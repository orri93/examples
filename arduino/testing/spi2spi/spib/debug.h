#ifndef FDS_MC_DEBUG_H_
#define FDS_MC_DEBUG_H_

#define SERIAL_INTERVAL  1000

#define FDS_SERIAL_OUTPUT_NONE   0
#define FDS_SERIAL_OUTPUT_DEBUG  1   /* General DEBUGING messages */
#define FDS_SERIAL_OUTPUT_CSV    2   /* Output a CSV log (good for PID) */
#define FDS_SERIAL_OUTPUT_KEY    3   /* Debug the press button keys */
#define FDS_SERIAL_OUTPUT_SYNC   4   /* Sync sensor */


#if FDS_SERIAL_OUTPUT == FDS_SERIAL_OUTPUT_DEBUG
#define FDS_IS_SERIAL_DEBUG
#define FDS_IS_DEBUG
#elif FDS_SERIAL_OUTPUT == FDS_SERIAL_OUTPUT_CSV
#define FDS_IS_SERIAL_CSV
#elif FDS_SERIAL_OUTPUT == FDS_SERIAL_OUTPUT_KEY
#define FDS_IS_SERIAL_KEY
#elif FDS_SERIAL_OUTPUT == FDS_SERIAL_OUTPUT_SYNC
#define FDS_IS_SERIAL_SYNC
#else
#define FDS_IS_SERIAL_NONE
#endif

#ifdef FDS_IS_SERIAL_NONE
#define FDS_DEBUG_BEGIN(...) /* Do nothing */
#else
#define FDS_DEBUG_BEGIN(...) Serial.begin(SERIAL_BAUD)
#endif

#ifdef FDS_IS_SERIAL_DEBUG
#define FDS_DEBUG(...) Serial.print(__VA_ARGS__)
#define FDS_DEBUGLN(...) Serial.println(__VA_ARGS__)
#else
#define FDS_DEBUG(...) /* Do nothing */
#define FDS_DEBUGLN(...) /* Do nothing */
#endif

#endif
