# File: YCSB-CXX/CMakeLists.txt Author: Michalis Vardoulakis
# <mvard@ics.forth.gr>

include_directories(BEFORE core db ../kreon ../kreon_server)

# FIXME  fix the include directive paths in ycsb's subfolders
add_executable(ycsb-kreon db/db_factory_kreonR.cc core/core_workload.cc
                          driver/ycsbc.cc ../kreon_server/globals.c)

target_link_libraries(ycsb-kreon kreon_client kreon_rdma kreonr)
set_target_properties(
  ycsb-kreon
  PROPERTIES LINK_FLAGS "-pthread -lm -lzookeeper_mt -lnuma -lrdmacm -libverbs"
             COMPILE_DEFINITIONS "KREON_DISTRIBUTED")

add_executable(ycsb-rdma-test ../kreon_server/globals.c db/db_factory_kreonR.cc
                              core/core_workload.cc driver/ycsbc.cc)

target_link_libraries(ycsb-rdma-test kreon_client kreon_rdma kreonr)
set_target_properties(
  ycsb-rdma-test
  PROPERTIES LINK_FLAGS "-pthread -lm -lzookeeper_mt -lnuma -lrdmacm -libverbs"
             COMPILE_DEFINITIONS "KREON_DISTRIBUTED")

add_executable(ycsb-edb db/db_factory_eutropiadb.cc core/core_workload.cc
                        driver/ycsbc.cc ../utilities/list.c)

target_link_libraries(ycsb-edb kreon)
set_target_properties(ycsb-edb PROPERTIES LINK_FLAGS "-pthread -lnuma")