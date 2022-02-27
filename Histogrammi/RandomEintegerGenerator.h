// ----------------- RandomEintegerGenerator.h ---------------

#ifndef RANDOMEINTEGERGENERATOR_H
#define RANDOMEINTEGERGENERATOR_H

#include <cstdlib>
#include <ctime>
#include "HistogramBase.h"

namespace Hist {

	class RandomEintegerGenerator : RandomEintegerGeneratorBase {
	public:
		RandomEintegerGenerator() { 
			std::srand(std::time(nullptr)); 
		};

		~RandomEintegerGenerator() {};

		EInteger operator()() {
			//we only have 0 - 4 sofar...
			return static_cast<EInteger>(std::rand() % 5);
		};
	};
}
#endif
