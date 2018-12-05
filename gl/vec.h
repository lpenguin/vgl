//
// Created by nikita on 2018-12-04.
//

#ifndef UPLOADBENCH_VEC_H
#define UPLOADBENCH_VEC_H
namespace gl {
	struct uiVec2 {
		union {
			struct {
				unsigned int width, height;
			};

			struct {
				unsigned int x, y;
			};

		};
	};

	struct uiVec3 {
		struct {
			unsigned int width, height, depth;
		};

		struct {
			unsigned int x, y, z;
		};
	};
}


#endif //UPLOADBENCH_VEC_H
