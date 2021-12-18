#include "datarefDB.h"

#include "datarefs.h"
#include <time.h>

XPLMDataRef drPitch;

int nrInList = 0;
int nrOfInts = 0;
int nrOfFloats = 0;

char intList[100][512];
char floatList[100][512];

int findDataRef(const char* name, XPLMDataRef* result) {
    *result = XPLMFindDataRef(name);
    if (*result == NULL) {
        debugLog("Error finding XPL variable ");
        debugLog(name);
        debugLog("\n");
        return -1;
    }
    return 0;
}

int createIntDR(const char* name) {

    int* valuepointer;
    valuepointer = malloc(sizeof(int));
    nrInList++;
    *valuepointer = nrInList;
    debugLog("pointer create .%s. value %d mem %d\n", name, nrInList, valuepointer);
    XPLMDataRef customDR = XPLMRegisterDataAccessor(name,
                                                    xplmType_Int, // The types we support
                                                    1,            // Writable
                                                    GetIntCB,
                                                    SetIntCB, // Integer accessors
                                                    NULL,
                                                    NULL, // Float accessors
                                                    NULL,
                                                    NULL, // Doubles accessors
                                                    NULL,
                                                    NULL, // Int array accessors
                                                    NULL,
                                                    NULL, // Float array accessors
                                                    NULL,
                                                    NULL, // Raw data accessors
                                                    valuepointer,
                                                    valuepointer); // Refcons
    // Find and intialize our dataref
    customDR = XPLMFindDataRef(name);
    if (customDR == NULL) {
        return -1;
    } else {
        XPLMSetDatai(customDR, 0);
        debugLog("Created int DR: %s\n", name);
        return 1;
    }
}

int createFloatDR(const char* name) {

    float* valuepointer;
    valuepointer = malloc(sizeof(float));
    *valuepointer = 0.0;
    XPLMDataRef customDR = XPLMRegisterDataAccessor(name,
                                                    xplmType_Float, // The types we support
                                                    1,              // Writable
                                                    NULL,
                                                    NULL, // Integer accessors
                                                    GetFloatCB,
                                                    SetFloatCB, // Float accessors
                                                    NULL,
                                                    NULL, // Doubles accessors
                                                    NULL,
                                                    NULL, // Int array accessors
                                                    NULL,
                                                    NULL, // Float array accessors
                                                    NULL,
                                                    NULL, // Raw data accessors
                                                    valuepointer,
                                                    valuepointer); // Refcons
    // Find and intialize our dataref
    customDR = XPLMFindDataRef(name);
    if (customDR == NULL)
        return -1;
    else {
        XPLMSetDataf(customDR, 0.0);
        debugLog("Created float DR: %s\n", name);
        return 1;
    }
}

int initDataRefs() {
    int lTmp;
    /* Also look up our data refs. */
    lTmp = 0;
    //lTmp += findDataRef("sim/flightmodel/position/theta", &drPitch);
    // lTmp += findDataRef("sim/flightmodel/position/theta", &drPitch);
    createIntDR("drdb/test/working0");
    for (int i = 0; i < nrOfInts; i++) {
        createIntDR(intList[i]);
    }
    createIntDR("drdb/test/working2");
    createIntDR("JAS/test/working2");
    createIntDR("JAS/test/working22");
    createIntDR("JAS/test/working23");
    createFloatDR("JAS/test/working24");

    return lTmp;
}

void unregisterData() {
    //XPLMUnregisterDataAccessor(hueDR);
}

void SetIntCB(void* inRefcon, int inValue) {

    *((int*)inRefcon) = inValue;
}
int GetIntCB(void* inRefcon) {

    // debugLog("pointer get value %d mem %d\n", *((int*)inRefcon), inRefcon);
    // int out = *((int*)inRefcon);
    return *((int*)inRefcon);
}

void SetFloatCB(void* inRefcon, float inValue) {
    *((float*)inRefcon) = inValue;
}
float GetFloatCB(void* inRefcon) {
    return *((float*)inRefcon);
}
