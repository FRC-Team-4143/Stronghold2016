/*
 * VisionSource.h
 *
 *  Created on: Mar 8, 2016
 *      Author: Anthony
 */

#ifndef SRC_MODULES_VISIONSOURCE_H_
#define SRC_MODULES_VISIONSOURCE_H_

class VisionSource : public PIDSource{
public:
	VisionSource();
	virtual ~VisionSource();
	double PIDGet();
};

#endif /* SRC_MODULES_VISIONSOURCE_H_ */
