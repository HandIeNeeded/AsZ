#!/bin/bash
#cp batch.sh future_net
cd future_net
rm ./bin/* -rf
make
cp ./bin/puzzle_solver_asz ./future_net
cd -
tar -zcPf future_net.tar.gz ./future_net

