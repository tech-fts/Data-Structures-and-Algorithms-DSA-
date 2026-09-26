#ifndef FUSHION_QUEUE_H
#define FUSHION_QUEUE_H

#include <stdint.h>
#include <stdbool.h>

typedef enum{
    SOURCR_WHEEL,
    SOURCE_GPS
} SourceData;

typedef struct 
{
    double x_position;
    double y_position;
    double heading;
}PositionInfo;

typedef struct Datapocket{
    uint64_t time_stamp;
    SourceData source;
    PositionInfo poinfo;
    struct Datapocket* next;
    struct Datapocket* pre;
}Datapocket;

typedef struct{
    Datapocket* head;
    Datapocket* tail;
    uint64_t max_history_ns;
}SensorBuffer;

void buffer_init(SensorBuffer* buffer, uint64_t max_history_ns);
void buffer_add_record(SensorBuffer* buffer, uint64_t timestamp, PositionInfo position, SourceData source);
void buffer_remove(SensorBuffer* buffer);
void buffer_clear(SensorBuffer* buffer);

bool buffer_estimate_position(const SensorBuffer* buffer, uint64_t target_time, PositionInfo* out_position);
PositionInfo buffer_add_gps(SensorBuffer* buffer, uint64_t gps_time, PositionInfo gps_postiton);


#endif