#!/bin/bash

for dir in `ls ./testdata`; do
    echo "Test $dir"
    ../bin/puzzle_solver_asz ./testdata/$dir/topo.csv ./testdata/$dir/demand.csv ./testdata/$dir/asz_result.csv
    cat ./testdata/$dir/asz_result.csv
    echo "-----------------------------------------------------------------------------------------------------"
done


