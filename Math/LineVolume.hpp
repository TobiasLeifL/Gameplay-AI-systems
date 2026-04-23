#pragma once
#include "vector.hpp"
#include "Line.hpp"
#include <vector>

namespace CommonUtilities
{
	template<class T>
	class LineVolume
	{
		public:
			LineVolume();
			LineVolume(const std::vector<Line<T>>& aLineList);

			void AddLine(const Line<T>& aLine);

			bool IsInside(const Vector2<T>& aPosition) const;

			std::vector<Line<T>>& GetLines();

		private:
			std::vector<Line<T>> myLines;
	};
	template<class T>
	inline LineVolume<T>::LineVolume()
	{

	}

	template<class T>
	inline LineVolume<T>::LineVolume(const std::vector<Line<T>>& aLineList)
	{
		myLines = aLineList;
	}

	template<class T>
	inline void LineVolume<T>::AddLine(const Line<T>& aLine)
	{
		myLines.push_back(aLine);
	}

	template<class T>
	inline bool LineVolume<T>::IsInside(const Vector2<T>& aPosition) const
	{

		bool isInside = true;
		for (int i = 0; i < myLines.size(); i++)
		{

			if (myLines[i].GetDotProductOnLine(aPosition) > 0)
			{
				isInside = false;
				break;
			}
		}
		return isInside;
	}

	template<class T>
	inline std::vector<Line<T>>& LineVolume<T>::GetLines()
	{
		return myLines;
	}
}