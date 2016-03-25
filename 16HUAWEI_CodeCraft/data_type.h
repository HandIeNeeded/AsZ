/*************************************************************************
	> File Name: data_type.h
	> Author: yuzhou627
	> Mail:   yuzhou627@gmail.com
	> created Time: Fri 25 Mar 2016 03:04:02 AM CST
*************************************************************************/

#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

#include <vector>
#include <string>
#include <map>
#include <set>
#include "data_io_helper.h"

namespace graph {
    template<class Type1, class Type2>
    struct Edge {
        Type1 start, end, index;
        Type2 length;
        Edge(Type1 start, Type1 end, Type1 index, Type2 length): start(start), end(end), index(index), length(length) {}
    };

    template<class Type1, class Type2>
    struct Node {
        Type1 inDegree, outDegree;
        Type2 importance;
        Node (Type2 importance): inDegree(0), outDegree(0), importance(importance) {}
        Node (Type1 in, Type1 out, Type2 importance): inDegree(in), outDegree(out), importance(importance) {}
    };

    template<class TypeNode1, class TypeNode2, class TypeEdge1, class TypeEdge2>
    class Graph {
    public:
        //node count, edge count
        int mNode, mEdge;
        std::vector<Node<TypeNode1, TypeNode2>> mNodes;
        std::vector<std::vector<Edge<TypeEdge1, TypeEdge2>>> mEdges;
        //key nodes, have to cover
        std::vector<Node<TypeNode1, TypeNode2>> mKeyNodes;
        //answer path
        std::vector<Edge<TypeEdge1, TypeEdge2>> mPaths;
    };
}

#endif /* _DATA_TYPE_H_ */
