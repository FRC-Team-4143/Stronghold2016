/*
 * VisionSink.h
 *
 *  Created on: Mar 8, 2016
 *      Author: Anthony
 */

#ifndef SRC_MODULES_VISIONSINK_H_
#define SRC_MODULES_VISIONSINK_H_

class VisionSink : public PIDOutput{
public:
	VisionSink();
	virtual ~VisionSink();
	double value;
	void PIDWrite(float output);
};

#endif /* SRC_MODULES_VISIONSINK_H_ */
