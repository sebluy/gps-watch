#ifndef WAYPOINT_WRITER_H
#define WAYPOINT_WRITER_H

/* A waypoint writer is used for storing waypoints in non-volatile storage.
   Use a waypoint reader to get waypoints out of storage.
   Only one waypoint path can be stored at any given time.
   Creating a new waypoint_writer and writing to it will overwrite the previous
   waypoint path. */

enum waypoint_field_t {COUNT, LATITUDE, LONGITUDE};

struct waypoint_writer_t {
    waypoint_field_t field;
    float *ptr;
};

void waypoint_writer_initialize(waypoint_writer_t *writer);

/* Writes a waypoint field to storage. After initialization, should
   be called successively with count, lat1, lng1, lat2, lng2, ...
   for "count" points. */
void waypoint_writer_write(waypoint_writer_t *writer, char *field);

#endif
