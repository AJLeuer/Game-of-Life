

#include "../Util/Util.hpp"

#include "DisplayData.hpp"

bool DisplayData::isInit = false ;

bool DisplayData::hiDPI_referenceVal ;

float DisplayData::displayScalingFactor_referenceVal ;

#ifndef __APPLE__
CGDirectDisplayID DisplayData::displayID = CGMainDisplayID() ;
CGDisplayModeRef DisplayData::displayMode = CGDisplayCopyDisplayMode(displayID) ;
#endif

void DisplayData::init() {
	
	/* init displayScalingFactor_referenceVal */
	calculateDisplayScalingFactor() ;
	
	/* init hiDPI_referenceVal */
	hiDPI_referenceVal = (displayScalingFactor_referenceVal == 2.0);
	
	isInit = true ;
	
}

#ifndef __APPLE__

/* non-OS X implementations: */
 
vec2<unsigned> DisplayData::calculateScreenResolution() {
	//todo
}

void DisplayData::calculateDisplayScalingFactor() {
	//todo
}

#endif

double DisplayData::getScreenRefreshRate() {
	return CGDisplayModeGetRefreshRate(displayMode) ;
}

const std::chrono::milliseconds DisplayData::getScreenRefreshInterval() {
    unsigned interval = 1000 / getScreenRefreshRate();
    return std::chrono::milliseconds(interval) ;
}

bool DisplayData::hiDPI() {

	if (isInit == false) {
		init() ;
		return DisplayData::hiDPI_referenceVal ;
	}
	else {
		return DisplayData::hiDPI_referenceVal ;
	}
	
}



