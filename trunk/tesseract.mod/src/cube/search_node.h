/**********************************************************************
 * File:        search_node.h
 * Description: Declaration of the Beam Search Node Class
 * Author:    Ahmad Abdulkader
 * Created:   2008
 *
 * (C) Copyright 2008, Google Inc.
 ** Licensed under the Apache License, Version 2.0 (the "License");
 ** you may not use this file except in compliance with the License.
 ** You may obtain a copy of the License at
 ** http://www.apache.org/licenses/LICENSE-2.0
 ** Unless required by applicable law or agreed to in writing, software
 ** distributed under the License is distributed on an "AS IS" BASIS,
 ** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ** See the License for the specific language governing permissions and
 ** limitations under the License.
 *
 **********************************************************************/

// The SearchNode class abstracts the search lattice node in the lattice
// generated by the BeamSearch class
// The SearchNode class holds the lang_mod_edge associated with the lattice
// node. It also holds a pointer to the parent SearchNode in the search path
// In addition it holds the recognition and the language model costs of the
// node and the path leading to this node

#ifndef SEARCH_NODE_H
#define SEARCH_NODE_H

#include "lang_mod_edge.h"
#include "cube_reco_context.h"

namespace tesseract {

class SearchNode {
 public:
  SearchNode(CubeRecoContext *cntxt, SearchNode *parent_node,
             int char_reco_cost, LangModEdge *edge, int col_idx);

  ~SearchNode();

  // Updates the parent of the current node if the specified path yields
  // a better path cost
  bool UpdateParent(SearchNode *new_parent, int new_reco_cost,
                    LangModEdge *new_edge);
  // returns the 32-bit string corresponding to the path leading to this node
  char_32 *PathString();
  // True if the two input nodes correspond to the same path
  static bool IdenticalPath(SearchNode *node1, SearchNode *node2);

  inline const char_32 *NodeString() { return str_; }
  inline void SetString(char_32 *str) { str_ = str; }

  // This node's character recognition cost.
  inline int CharRecoCost() { return char_reco_cost_; }
  // Total character recognition cost of the nodes in the best path,
  // excluding this node.
  inline int BestPathRecoCost() { return best_path_reco_cost_; }
  // Number of nodes in best path.
  inline int BestPathLength() { return best_path_len_; }
  // Mean mixed cost, i.e., mean character recognition cost +
  // current language model cost, all weighted by the RecoWgt parameter
  inline int BestCost() { return best_cost_; }
  // Mean character recognition cost of the nodes on the best path,
  // including this node.
  inline int BestRecoCost() { return mean_char_reco_cost_ ; }

  inline int ColIdx() { return col_idx_; }
  inline SearchNode *ParentNode() { return parent_node_; }
  inline LangModEdge *LangModelEdge() { return lang_mod_edge_;}
  inline int LangModCost() { return LangModCost(lang_mod_edge_, parent_node_); }

  // A comparer function that allows the SearchColumn class to sort the
  // nodes based on the path cost
  inline static int SearchNodeComparer(const void *node1, const void *node2) {
    return (*(reinterpret_cast<SearchNode * const *>(node1)))->best_cost_ -
        (*(reinterpret_cast<SearchNode * const *>(node2)))->best_cost_;
  }

 private:
  CubeRecoContext *cntxt_;
  // Character code
  const char_32 *str_;
  // Recognition cost of most recent character
  int char_reco_cost_;
  // Mean mixed cost,  i.e., mean character recognition cost +
  // current language model cost, all weighted by the RecoWgt parameter
  int best_cost_;
  // Mean character recognition cost of the nodes on the best path,
  // including this node.
  int mean_char_reco_cost_ ;
  // Total character recognition cost of the nodes in the best path,
  // excluding this node.
  int best_path_reco_cost_;
  // Number of nodes in best path.
  int best_path_len_;
  // Column index
  int col_idx_;
  // Parent Node
  SearchNode *parent_node_;
  // Language model edge
  LangModEdge *lang_mod_edge_;
  static int LangModCost(LangModEdge *lang_mod_edge, SearchNode *parent_node);
};

// Implments a SearchNode hash table used to detect if a Search Node exists
// or not. This is needed to make sure that identical paths in the BeamSearch
// converge
class SearchNodeHashTable {
 public:
  SearchNodeHashTable() {
    memset(bin_size_array_, 0, sizeof(bin_size_array_));
  }

  ~SearchNodeHashTable() {
  }

  // inserts an entry in the hash table
  inline bool Insert(LangModEdge *lang_mod_edge, SearchNode *srch_node) {
    // compute hash based on the edge and its parent node edge
    unsigned int edge_hash = lang_mod_edge->Hash();
    unsigned int parent_hash = (srch_node->ParentNode() == NULL ?
        0 : srch_node->ParentNode()->LangModelEdge()->Hash());
    unsigned int hash_bin = (edge_hash + parent_hash) % kSearchNodeHashBins;

    // already maxed out, just fail
    if (bin_size_array_[hash_bin] >= kMaxSearchNodePerBin) {
      return false;
    }

    bin_array_[hash_bin][bin_size_array_[hash_bin]++] = srch_node;

    return true;
  }

  // Looks up an entry in the hash table
  inline SearchNode *Lookup(LangModEdge *lang_mod_edge,
                            SearchNode *parent_node) {
    // compute hash based on the edge and its parent node edge
    unsigned int edge_hash = lang_mod_edge->Hash();
    unsigned int parent_hash = (parent_node == NULL ?
        0 : parent_node->LangModelEdge()->Hash());
    unsigned int hash_bin = (edge_hash + parent_hash) % kSearchNodeHashBins;

    // lookup the entries in the hash bin
    for (int node_idx = 0; node_idx < bin_size_array_[hash_bin]; node_idx++) {
      if (lang_mod_edge->IsIdentical(
          bin_array_[hash_bin][node_idx]->LangModelEdge()) == true &&
          SearchNode::IdenticalPath(
          bin_array_[hash_bin][node_idx]->ParentNode(), parent_node) == true) {
        return bin_array_[hash_bin][node_idx];
      }
    }

    return NULL;
  }

 private:
  // Hash bin size parameters. These were determined emperically. These affect
  // the speed of the beam search but have no impact on accuracy
  static const int kSearchNodeHashBins = 4096;
  static const int kMaxSearchNodePerBin = 512;
  int bin_size_array_[kSearchNodeHashBins];
  SearchNode *bin_array_[kSearchNodeHashBins][kMaxSearchNodePerBin];
};
}

#endif  // SEARCH_NODE_H
