
#ifndef DATAREF_H_INCLUDED
#define DATAREF_H_INCLUDED

#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"
#include "XPLMPlugin.h"
#include "XPLMPlanes.h"

extern int nrOfInts;
extern int nrOfFloats;

extern char intList[][512];
extern char floatList[][512];

int findDataRef(const char* name, XPLMDataRef* result);

int registerDataRefs();

int initDataRefs();
void unregisterData();

int createIntDR(const char* name);
int createFloatDR(const char* name);

void SetIntCB(void* inRefcon, int inValue);
int GetIntCB(void* inRefcon);

void SetFloatCB(void* inRefcon, float inValue);
float GetFloatCB(void* inRefcon);

#endif
