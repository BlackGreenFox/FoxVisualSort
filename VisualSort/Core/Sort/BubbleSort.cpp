#include "BubbleSort.h"


BubbleSort::BubbleSort()
{
    _values = nullptr;
    _paused = true;
    _i = 0;
    _j = 0;
    _delay = 0;
    _swapped = false;
    _last_step = SDL_GetTicks();
    _comparison_state = 0.0f;
    _sorted = false;
}

void BubbleSort::Init(std::vector<int>& values, int delay) {
    _values = &values;
    _paused = true;
    _i = 0;
    _j = 0;
    _delay = delay;
    _swapped = false;
    _last_step = SDL_GetTicks();
    _comparison_state = 0.0f;
    _sorted = false;
}
 

void BubbleSort::Step() {
    if (_paused || _values == nullptr || _i >= _values->size() - 1) {
        return;
    }

    Uint32 current_time = SDL_GetTicks();
    if (current_time - _last_step < _delay) {
        return;
    }
    _last_step = current_time;

    if (_j < _values->size() - _i - 1) {
        // Increment comparison counter
        if ((*_values)[_j] > (*_values)[_j + 1]) {
            std::swap((*_values)[_j], (*_values)[_j + 1]);
            _swapped = true;
            _comparison_state++;  // Reset comparison counter on swap
        }
        else {
            _comparison_state = 0;
        }
        _j++;
    }
    else {
        if (!_swapped) {
            _i = _values->size();
            _sorted = true;  // Indicate that the array is sorted
        }
        _j = 0;
        _i++;
        _swapped = false;
    }
}

void BubbleSort::Update(SDL_Renderer* renderer, int offsetX, int offsetY, int width, int height) {
    if (_values == nullptr) return;

    int margin = 10;
    int available_width = width - 2 * margin;
    int available_height = height - 2 * margin;
    int num_values = _values->size();
    int line_gap = 1;   
    int line_width = (available_width - (num_values - 1) * line_gap) / num_values;
    int thick_line_width = std::max(1, line_width);

    for (int i = 0; i < num_values; ++i) {
        if (_sorted) {
            SDL_SetRenderDrawColor(renderer, 144, 238, 144, 255);  // Light green when sorted
        }
        else if (i == _j || i == _j + 1) {
            SDL_SetRenderDrawColor(renderer, 99, 220, 66, 255);    // Highlight the current sorting elements
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Default color
        }

        // Line Draw
        SDL_Rect lineRect = {
            offsetX + margin + i * (thick_line_width + line_gap),
            height - margin - ((*_values)[i] * available_height / 100),
            thick_line_width,
            (*_values)[i] * available_height / 100
        };
        SDL_RenderFillRect(renderer, &lineRect);
    }
}

std::string BubbleSort::GetDescription() const {
    return "Bubble sort, sometimes referred to as sinking sort, is a simple sorting algorithm that repeatedly steps through the input list element by element, comparing the current element with the one after it, swapping their values if needed. These passes through the list are repeated until no swaps have to be performed during a pass, meaning that the list has become fully sorted. The algorithm, which is a comparison sort, is named for the way the larger elements 'bubble' up to the top of the list.";
}

std::vector<float> BubbleSort::GetBigOPlotData() const {
    std::vector<float> big_o_plot(_values->size());
    for (size_t i = 0; i < _values->size(); ++i) {
        big_o_plot[i] = static_cast<float>(i * i);  
    }
    return big_o_plot;
}
