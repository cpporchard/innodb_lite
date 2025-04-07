cmake_minimum_required(VERSION 3.29)
project(innobase_mini)

set(CMAKE_CXX_STANDARD 20)

add_executable(innobase_lite mysqld.cc
        sql/iterators/basic_row_iterators.cc
        sql/iterators/basic_row_iterators.h
        sql/iterators/row_iterator.h
        sql/table.h
        sql/handler.h
        sql/handler.cc
        storage/innobase/a0_handler/ha_innodb.cc
        storage/innobase/a0_handler/ha_innodb.h
        storage/innobase/c_row/row0sel.cc
        storage/innobase/b0_trx/trx0trx.h
        storage/innobase/d0_btr/btr0pcur.h
        storage/innobase/d0_btr/btr0pcur.cc
        storage/innobase/d0_btr/btr0btr.h
        storage/innobase/e_buf/buf0buf.h
        storage/innobase/e_buf/buf0buf.cc
        storage/innobase/f_page/page0curr.cc
        storage/innobase/f_page/page0page.h
        storage/innobase/d0_btr/btr0btr.cc
        storage/innobase/f_page/page0types.h
        storage/innobase/c_row/row0mysql.h
        storage/innobase/f_page/page0cur.h
        storage/innobase/d2_mtr_later/mtr0mtr.h
        storage/innobase/d0_btr/btr0cur.cc
        storage/innobase/c_row/row0sel.h
        storage/innobase/b0_trx/trx0trx.cc
        storage/innobase/g_log_redo_wal/log0log.cc
        storage/innobase/d2_mtr_later/mtr0mtr.cc
        storage/innobase/e_buf/buf0rea.cc
        storage/innobase/z_fil_later/fil0fil.cc
        storage/innobase/e_buf/buf0flu.cc
        storage/innobase/b1_read_later/read0read.h
        storage/innobase/b0_trx/trx0sys.h
)
