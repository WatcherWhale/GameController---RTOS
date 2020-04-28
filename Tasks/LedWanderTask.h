#ifndef LEDWANDERTASK_H_
#define LEDWANDERTASK_H_


void InitLedWanderTask(void);
static void LedWanderJob(void *pvParameters);
static void DirectionChangeJob(void *pvParameters);

#endif