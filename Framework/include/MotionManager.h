/*
 *   MotionManager.h
 *
 *   Author: ROBOTIS
 *
 */

#ifndef _MOTION_MANGER_H_
#define _MOTION_MANGER_H_

#include <list>
#include <fstream>
#include <iostream>
#include "MotionStatus.h"
#include "MotionModule.h"
#include "CM730.h"
#include "minIni.h"
#include "AngleEstimator.h"

#define OFFSET_SECTION "Offset"
#define INVALID_VALUE   -1024.0

namespace Robot
{
	class MotionManager
	{
		private:
			static MotionManager* m_UniqueInstance;
			std::list<MotionModule*> m_Modules;
			CM730 *m_CM730;
			bool m_ProcessEnable;
			bool m_Enabled;
			int m_FBGyroCenter;
			int m_RLGyroCenter;
			int m_CalibrationStatus;

			bool m_IsRunning;
			bool m_IsThreadRunning;
			bool m_IsLogging;

			int m_Torque[JointData::NUMBER_OF_JOINTS];

			std::ofstream m_LogFileStream;

			AngleEstimator m_angleEstimator;
			bool m_fadeIn;
			int m_torque_count;

			FILE* m_voltageLog;

			unsigned int m_torqueAdaptionCounter;
			double m_voltageAdaptionFactor;

			MotionManager();

			void adaptTorqueToVoltage();

		protected:

		public:
			bool DEBUG_PRINT;
			int m_Offset[JointData::NUMBER_OF_JOINTS];

			~MotionManager();

			static MotionManager* GetInstance() { return m_UniqueInstance; }

			bool Initialize(CM730 *cm730, bool fadeIn = true);
			bool Reinitialize();
			void Process();
			void SetEnable(bool enable);
			bool GetEnable()				{ return m_Enabled; }
			void AddModule(MotionModule *module);
			void RemoveModule(MotionModule *module);

			void SetTorque(int id, bool enable);

			void ResetGyroCalibration() { m_CalibrationStatus = 0; m_FBGyroCenter = 512; m_RLGyroCenter = 512; }
			int GetCalibrationStatus() { return m_CalibrationStatus; }
			void SetJointDisable(int index);

			void StartLogging();
			void StopLogging();

			void LoadINISettings(minIni* ini);
			void LoadINISettings(minIni* ini, const std::string &section);
			void SaveINISettings(minIni* ini);
			void SaveINISettings(minIni* ini, const std::string &section);

			inline AngleEstimator* angleEstimator()		{ return &m_angleEstimator; }
	};
}

#endif
