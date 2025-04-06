/** @file sql/handler.cc

    @brief
    Implements functions in the handler interface that are shared between all
    storage engines.
*/

/**
  @def MYSQL_TABLE_IO_WAIT
  Instrumentation helper for table io_waits.
  Note that this helper is intended to be used from
  within the handler class only, as it uses members
  from @c handler
  Performance schema events are instrumented as follows:
  - in non batch mode, one event is generated per call
  - in batch mode, the number of rows affected is saved
  in @c m_psi_numrows, so that @c end_psi_batch_mode()
  generates a single event for the batch.
  @param OP the table operation to be performed
  @param INDEX the table index used if any, or MAX_KEY.
  @param RESULT the result of the table operation performed
  @param PAYLOAD instrumented code to execute
  @sa handler::end_psi_batch_mode.
*/

#include "handler.h"

#ifdef HAVE_PSI_TABLE_INTERFACE
#define MYSQL_TABLE_IO_WAIT(OP, INDEX, RESULT, PAYLOAD)                     \
  {                                                                         \
    if (m_psi != nullptr) {                                                 \
      switch (m_psi_batch_mode) {                                           \
        case PSI_BATCH_MODE_NONE: {                                         \
          PSI_table_locker *sub_locker = nullptr;                           \
          PSI_table_locker_state reentrant_safe_state;                      \
          reentrant_safe_state.m_thread = nullptr;                          \
          reentrant_safe_state.m_wait = nullptr;                            \
          sub_locker = PSI_TABLE_CALL(start_table_io_wait)(                 \
              &reentrant_safe_state, m_psi, OP, INDEX, __FILE__, __LINE__); \
          PAYLOAD                                                           \
          if (sub_locker != nullptr) PSI_TABLE_CALL(end_table_io_wait)      \
          (sub_locker, 1);                                                  \
          break;                                                            \
        }                                                                   \
        case PSI_BATCH_MODE_STARTING: {                                     \
          m_psi_locker = PSI_TABLE_CALL(start_table_io_wait)(               \
              &m_psi_locker_state, m_psi, OP, INDEX, __FILE__, __LINE__);   \
          PAYLOAD                                                           \
          if (RESULT != HA_ERR_END_OF_FILE) m_psi_numrows++;                \
          m_psi_batch_mode = PSI_BATCH_MODE_STARTED;                        \
          break;                                                            \
        }                                                                   \
        case PSI_BATCH_MODE_STARTED:                                        \
        default: {                                                          \
          assert(m_psi_batch_mode == PSI_BATCH_MODE_STARTED);               \
          PAYLOAD                                                           \
          if (RESULT != HA_ERR_END_OF_FILE) m_psi_numrows++;                \
          break;                                                            \
        }                                                                   \
      }                                                                     \
    } else {                                                                \
      PAYLOAD                                                               \
    }                                                                       \
  }
#else
#define MYSQL_TABLE_IO_WAIT(OP, INDEX, RESULT, PAYLOAD) PAYLOAD
#endif



/**
  Initialize table for random read or scan.

  @param scan  if true: Initialize for random scans through rnd_next()
               if false: Initialize for random reads through rnd_pos()

  @return Operation status
    @retval 0     Success
    @retval != 0  Error (error code returned)
*/

int handler::ha_rnd_init(bool scan) {
  int result;
  inited = (result = rnd_init(scan)) ? NONE : RND;
  end_range = nullptr;
  return result;
}

/**
  Read next row via random scan.

  @param buf  Buffer to read the row into

  @return Operation status
    @retval 0     Success
    @retval != 0  Error (error code returned)
*/

int handler::ha_rnd_next(uchar *buf) {
    int result;

    // Set status for the need to update generated fields
    m_update_generated_read_fields = table->has_gcol();

    MYSQL_TABLE_IO_WAIT(PSI_TABLE_FETCH_ROW, MAX_KEY, result, { result = rnd_next(buf); })
    if (!result && m_update_generated_read_fields) {
        result = update_generated_read_fields(buf, table);
        m_update_generated_read_fields = false;
    }

    return result;
}
