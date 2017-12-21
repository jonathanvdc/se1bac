#pragma once

#include <functional>
#include <memory>
#include "IParser.h"

namespace Arcade
{
	/// \brief An IParser implementation that uses a function under the hood.
	template<typename TSource, typename TTarget>
	class LambdaParser : public virtual IParser<TSource, TTarget>
	{
	public:
		LambdaParser(std::function<TTarget(TSource)> Lambda)
			: val(Lambda)
		{ }

		/// \brief Creates a new lambda parser from the given parser function.
		static std::shared_ptr<LambdaParser<TSource, TTarget>> make_shared(std::function<TTarget(TSource)> Lambda)
		{
			return std::make_shared<LambdaParser<TSource, TTarget>>(Lambda);
		}

		/// \brief Creates a new lambda parser from the given parser member function.
		template<typename TThis>
		static std::shared_ptr<LambdaParser<TSource, TTarget>> make_shared(TThis& ThisValue, TTarget(TThis::*Lambda)(TSource) const)
		{
			return make_shared(std::bind(Lambda, &ThisValue, std::placeholders::_1));
		}

		/// \brief Parses the given argument and returns the result.
		TTarget Parse(TSource Arg) const override { return this->val(Arg); }

	private:
		std::function<TTarget(TSource)> val;
	};
}
