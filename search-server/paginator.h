#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
        : begin_(begin), end_(end) {
    }

    Iterator begin() const {
        return begin_;
    }

    Iterator end() const {
        return end_;
    }

    int size() {
        return distance(begin_, end_);
    }

private:
    Iterator begin_;
    Iterator end_;
};

template <typename Iterator >
std::ostream& operator<<(std::ostream& output, const IteratorRange<Iterator>& iter) {
    for (Iterator nachalo = iter.begin(); nachalo != iter.end(); ++nachalo) {
        output << *nachalo;
    }
    return output;
}

template <typename Iterator >
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, int size) {
        for (auto begin_page = begin; begin_page != end; ) {
            if (distance(begin_page, end) > size) {
                auto end_page = next(begin_page, size);
                paginators_.push_back({ begin_page, end_page });
                begin_page = end_page;
            }
            else {
                paginators_.push_back({ begin_page,end });
                begin_page = end;
            }
        }
    }

    auto begin() const {
        return paginators_.begin();
    }

    auto end() const {
        return paginators_.end();
    }

    int size() {
        return paginators_.size();
    }

private:
    std::vector <IteratorRange<Iterator>> paginators_;
};

template <typename Container>
auto Paginate(const Container& c, int page_size) {
    return Paginator(begin(c), end(c), page_size);
}