

#include "../Util/Util.hpp"

#include "DisplayData.hpp"

bool DisplayData::isInit = false ;

bool DisplayData::highDPIReferenceValue ;

float DisplayData::displayScalingFactorReferenceValue ;

#ifndef __APPLE__
CGDirectDisplayID DisplayData::displayID = CGMainDisplayID() ;
CGDisplayModeRef DisplayData::displayMode = CGDisplayCopyDisplayMode(displayID) ;
#endif

void DisplayData::init() {
	
	/* init displayScalingFactorReferenceValue */
	calculateDisplayScalingFactor() ;
	
	/* init highDPIReferenceValue */
	highDPIReferenceValue = (displayScalingFactorReferenceValue == 2.0);
	
	isInit = true ;
	
}

/* non-OS X implementations: */
 
vec2<unsigned> DisplayData::calculateScreenResolution() {
	return {1440, 900};
}

void DisplayData::calculateDisplayScalingFactor() {
	//todo
}


double DisplayData::getScreenRefreshRate() {
	return 120;
}

const std::chrono::milliseconds DisplayData::getScreenRefreshInterval() {
    unsigned interval = 1000 / getScreenRefreshRate();
    return std::chrono::milliseconds(interval) ;
}

bool DisplayData::hiDPI() {

	if (isInit == false) {
		init() ;
		return DisplayData::highDPIReferenceValue ;
	}
	else {
		return DisplayData::highDPIReferenceValue ;
	}
	
}



