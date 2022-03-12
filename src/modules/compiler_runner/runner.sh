#!/bin/bash
# Number of runs
num_starts=1

n_jobs=1
# Input size
input_x=1
input_y=1


current_directory=''
compiler_directory=''

weights_verification_file=''
bias_verification_file=''
scale_verification_file=''

warning_data_log=''
runtime_data_log=''

test_json_path=''
weights_path=''
hpm_weights_path=''
tpu_data_path=''


while [ -n "$1" ]
do
case "$1" in
    --n_starts) num_starts=$2;;
    --n_jobs) n_jobs=$2;;
    --input_x) input_x=$2;;
    --input_y) input_y=$2;;
    --current_dir) current_directory=$2;;
    --compiler_dir) compiler_directory=$2;;
    --wver) weights_verification_file=$2;;
    --bver) bias_verification_file=$2;;
    --sver) scale_verification_file=$2;;
    --warning) warning_data_log=$2;;
    --runtime) runtime_data_log=$2;;
    --json) test_json_path=$2;;
	--weights) weights_path=$2;;
	--hpm_weights) hpm_weights_path=$2;;
	--tpu_data) tpu_data_path=$2;;
    *) ;;
esac
shift
done

cd $compiler_directory

for ((i=0; i < $num_starts; i++))
do
    rm $weights_verification_file*  2> /dev/null
    rm $bias_verification_file*  2> /dev/null
    rm $scale_verification_file*  2> /dev/null
    make clean > /dev/null
    make --jobs=$n_jobs 2> $warning_data_log 1> $runtime_data_log
    ./hpm_scheduler -system=ivatpu -in_x=$input_x -in_y=$input_y -in_depth=3 -in_desc=$test_json_path -in_weights=$weights_path -out_weights=$hpm_weights_path -data_format=channel -gen_weights=false -stage=1 > $tpu_data_path
    rm layer*.bin 2> /dev/null
    grep -A11 "filters" $test_json_path > addrs.dat
done

cd $current_directory