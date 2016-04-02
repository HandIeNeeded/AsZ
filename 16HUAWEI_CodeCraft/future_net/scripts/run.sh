#!/bin/bash

if (( $# == 1 )); then 
    echo "Test on randomly generated tests!!!"
    ../bin/puzzle_solver_asz 
else 
    for dir in `ls ./testdata`; do
        echo "Test $dir"
        output="result.csv"
        ../bin/puzzle_solver_asz ./testdata/$dir/topo.csv ./testdata/$dir/demand.csv ./testdata/$dir/$output 2> ./testdata/$dir/runtime_log
        cat ./testdata/$dir/$output
        echo "runtime log: "
        cat ./testdata/$dir/runtime_log
        echo "-----------------------------------------------------------------------------------------------------"
    done
fi


