#pragma once
#ifndef TRDROP_POSTPROCESS_TASKS_H
#define TRDROP_POSTPROCESS_TASKS_H

#include <functional>

#include <opencv2/core.hpp>

namespace trdrop {
	namespace tasks {

		// preprocessing task which gets
		// * the previous frame
		// * the current frame
		// * the frame index
		//
		// these tasks will be ran asynchronous with threads because we only read from the frames
		// therefore they have to be commutative
		using pretask = std::function<void(const cv::Mat & prev, const cv::Mat & cur, const int currentFrame)>;

		// postprocessing task which gets
		// * the resulting frame which is to be modified
		//
		// these task should be appended in order to the schedueler because they modify the written frame
		using posttask = std::function<void(cv::Mat & res)>;

	} // namespace tasks
} //namespace trdrop

#endif // ! TRDROP_POSTPROCESS_TASKS_H