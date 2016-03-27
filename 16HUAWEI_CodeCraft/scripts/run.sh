#!/bin/bash

for dir in `ls ./testdata`; do
    echo "Test $dir"
    ../bin/puzzle_solver_asz ./testdata/$dir/topo.csv ./testdata/$dir/demand.csv ./testdata/$dir/asz_result.csv 2> runtime_log
    cat ./testdata/$dir/asz_result.csv
    echo ""
    echo "-----------------------------------------------------------------------------------------------------"
done


