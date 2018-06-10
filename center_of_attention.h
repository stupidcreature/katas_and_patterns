//For this kata, we're given an image in which some object of interest (e.g. a face, or a license plate, or an aircraft) appears as a large block of contiguous pixels all of the same colour. (Probably some image-processing has already occurred to achieve this, but we needn't worry about that.) We want to find the centre of the object in the image.
//
//We'll do this by finding which pixels of the given colour have maximum depth. The depth of a pixel P is the minimum number of steps (up, down, left, or right) you have to take from P to reach either a pixel of a different colour or the edge of the image.
//
//pixel depths pic
//
//        In the picture, the red pixel marked "3" has a depth of 3: it takes at least 3 steps from there to reach something other than another red pixel. Note that the steps need not be all in the same direction. Only one red pixel has depth 3: the one right in the middle of the red region. Similarly, the blue pixel marked "2" has a depth of 2 (but it is not the only one with this depth). The green and purple pixels all have depth 1.
//
//The pixels of a given colour with the largest depth will be found at the centre of the biggest solid region of that colour. Those are the ones we want.
//
//The function you'll write (central_pixels) belongs to the following data structure:
//
//struct Image
//{
//    unsigned *pixels;
//    unsigned width, height;
//
//    vector<unsigned> central_pixels(unsigned colour) const;
//    // other functions ...
//};
//
//The image data consists of a one-dimensional array pixels of unsigned integers (or just integers, in languages that don't have unsigned integers as such), which correspond to pixels in row-by-row order. (That is, the top row of pixels comes first, from left to right, then the second row, and so on, with the pixel in the bottom right corner last of all.) The values of the pixels array elements represent colours via some one-to-one mapping whose details need not concern us.
//
//The central_pixels function should find and return all the positions (pixels array indices) of the pixels having the greatest depth among all pixels of colour colour).
//
//Note 1. The final test in the suite (Big_Test) is a 16-megapixel image (4 megapixels in the Python version), so you will need to consider the time and space requirements of your solution for images up to that size.
//
//Note 2. The data in an Image object should not be assumed to be constant after instantiation. The test suite frequently modifies images and then re-tests them.
//
//Hint. It is possible to get this done in two passes through the pixel data.
//

#ifndef TEST02_CENTER_OF_ATTENTION_H
#define TEST02_CENTER_OF_ATTENTION_H

#include <igloo/igloo_alt.h>
using namespace igloo;

#include <vector>
using namespace std;

#include <algorithm>
#include <cmath>
#include <map>

struct Image {
    unsigned* pixels;
    unsigned  width, height;
    Image(std::vector<unsigned int>, unsigned width, unsigned height);
    virtual ~Image()
    {
        delete[] pixels;
    }

    vector<unsigned> central_pixels(unsigned colour) const;
};


Image::Image(std::vector<unsigned int> _pixels, unsigned _width, unsigned _height)
    : width{ _width }
    , height{ _height }
{
    pixels       = new unsigned[width * height];
    unsigned idx = 0;
    for (const auto p : _pixels) {
        pixels[idx++] = p;
    }
}

std::map<unsigned, unsigned>::const_iterator cpp14_max_element(std::map<unsigned, unsigned>::const_iterator first,
                                                               std::map<unsigned, unsigned>::const_iterator last)
{
    if (first == last) {
        return last;
    }

    auto largest = first;
    ++first;
    for (; first != last; ++first) {
        if (largest->second < first->second) {
            largest = first;
        }
    }
    return largest;
}

vector<unsigned> Image::central_pixels(unsigned color) const
{
    std::map<unsigned, unsigned> index_to_depth;
    std::vector<unsigned>        stack;
    bool                         in = false;

    enum class depth_mode { horizontal,
                            vertical };
    auto depth_from_stack = [&index_to_depth, &in, &stack](depth_mode mode) {
        bool     is_even     = (stack.size() % 2 == 0);
        auto     max_depth   = static_cast<unsigned>(std::ceil(stack.size() / 2.0));
        unsigned curdepth    = 1;
        int      depth_delta = 1;

        if (stack.size() < 3) {
            depth_delta = 0;
        }

        for (const auto idx : stack) {
            if (mode == depth_mode::horizontal || index_to_depth[idx] > curdepth) {
                index_to_depth[idx] = curdepth;
            }
            curdepth += depth_delta;
            if (curdepth == max_depth) {
                if (is_even) {
                    is_even     = false;
                    depth_delta = 0;
                } else {
                    depth_delta = -1;
                }
            }
        }
        stack.clear();
        in = false;
    };


    // horizontal
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            const std::size_t index = y * width + x;
            if (color == pixels[index]) {
                stack.push_back(index);
                in = true;
            } else if (in) {
                depth_from_stack(depth_mode::horizontal);
            }
        }
        depth_from_stack(depth_mode::horizontal);
    }


    // vertical
    for (unsigned x = 0; x < width; ++x) {
        for (unsigned y = 0; y < height; ++y) {
            const std::size_t index = y * width + x;
            if (color == pixels[index]) {
                stack.push_back(index);
                in = true;
            } else if (in) {
                depth_from_stack(depth_mode::vertical);
            }
        }
        depth_from_stack(depth_mode::vertical);
    }


    auto max_element_value = cpp14_max_element(std::cbegin(index_to_depth),
                                               std::cend(index_to_depth));
    if (max_element_value->second == 0)
        return {};

    std::vector<unsigned> central_indices;
    auto                  is_equal_to_max_element_value = [max_value = max_element_value->second](const auto& val) { return val.second == max_value; };
    auto                  it                            = std::find_if(std::begin(index_to_depth), std::end(index_to_depth), is_equal_to_max_element_value);
    while (it != std::end(index_to_depth)) {
        central_indices.emplace_back(it->first);
        it = std::find_if(std::next(it), std::end(index_to_depth), is_equal_to_max_element_value);
    }

    return central_indices;
}


vector<unsigned> sorted(const vector<unsigned>& v);

/* ---------------------------------------------------------------------------------- */
/*                               TESTS                                                */
/* ---------------------------------------------------------------------------------- */

Describe(Centre_of_attention){
    It(Example_In_The_Picture){
        Image image({ 1, 1, 4, 4, 4, 4, 2, 2, 2, 2,
                      1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
                      1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
                      1, 1, 1, 1, 1, 3, 2, 2, 2, 2,
                      1, 1, 1, 1, 1, 3, 3, 3, 2, 2,
                      1, 1, 1, 1, 1, 1, 3, 3, 3, 3 },
                    10, 6);

// Only one red pixel has the maximum depth of 3:
vector<unsigned> red_ctr = { 32 };
Assert::That(image.central_pixels(1), Equals(red_ctr));

// Multiple blue pixels have the maximum depth of 2:
vector<unsigned> blue_ctr = { 16, 17, 18, 26, 27, 28, 38 };
Assert::That(sorted(image.central_pixels(2)), Equals(blue_ctr));

// All the green pixels have depth 1, so they are all "central":
vector<unsigned> green_ctr = { 35, 45, 46, 47, 56, 57, 58, 59 };
Assert::That(sorted(image.central_pixels(3)), Equals(green_ctr));

// Similarly, all the purple pixels have depth 1:
vector<unsigned> purple_ctr = { 2, 3, 4, 5 };
Assert::That(sorted(image.central_pixels(4)), Equals(purple_ctr));

// There are no pixels with colour 5:
vector<unsigned> non_existent_ctr = {};
Assert::That(sorted(image.central_pixels(5)), Equals(non_existent_ctr));
}
}
;

/* ---------------------------------------------------------------------------------- */

vector<unsigned> sorted(const vector<unsigned>& v)
{
    vector<unsigned> sv(v);
    sort(sv.begin(), sv.end());
    return sv;
}


void center_of_attention()
{
    TestRunner::RunAllTests(0, nullptr);
}
#endif //TEST02_CENTER_OF_ATTENTION_H
