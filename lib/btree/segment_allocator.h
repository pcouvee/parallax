#pragma once
#include "../allocator/log_structures.h"
#include "../allocator/volume_manager.h"
#include "btree.h"
#include <stdint.h>

/*functions for index nodes*/
index_node *seg_get_index_node(struct db_descriptor *db_desc, uint8_t level_id, uint8_t tree_id, char reason);

index_node *seg_get_index_node_header(struct db_descriptor *db_desc, uint8_t level_id, uint8_t tree_id);

IN_log_header *seg_get_IN_log_block(struct db_descriptor *db_desc, uint8_t level_id, uint8_t tree_id);

void seg_free_index_node_header(struct db_descriptor *db_desc, uint8_t level_id, uint8_t tree_id, node_header *node);

void seg_free_index_node(struct db_descriptor *db_desc, uint8_t level_id, uint8_t tree_id, index_node *inode);

/*function for leaf nodes*/
leaf_node *seg_get_leaf_node(struct db_descriptor *db_desc, uint8_t level_id, uint8_t tree_id);

leaf_node *seg_get_leaf_node_header(struct db_descriptor *db_desc, uint8_t level_id, uint8_t tree_id);

void seg_free_leaf_node(struct db_descriptor *db_desc, uint8_t level_id, uint8_t tree_id, leaf_node *leaf);

struct bt_dynamic_leaf_node *seg_get_dynamic_leaf_node(struct db_descriptor *db_desc, uint8_t level_id,
						       uint8_t tree_id);
/*log related*/
segment_header *seg_get_raw_log_segment(struct db_descriptor *db_desc, enum log_type log_type, uint8_t level_id,
					uint8_t tree_id);

struct segment_header *get_segment_for_lsm_level_IO(struct db_descriptor *db_desc, uint8_t level_id, uint8_t tree_id);

uint64_t seg_free_level(struct db_descriptor *db_desc, uint64_t txn_id, uint8_t level_id, uint8_t tree_id);
void seg_zero_level(struct db_descriptor *db_desc, uint8_t level_id, uint8_t tree_id);

/*deprecated*/
void *get_space_for_system(volume_descriptor *volume_desc, uint32_t size, int lock);
