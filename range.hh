#ifndef Z_AKR_RANGE_HH
#define Z_AKR_RANGE_HH

#include <concepts>

namespace akr
{
    template<std::integral T>
    struct Range final
    {
        private:
        struct RangeIterator final
        {
            private:
            T currentIndex;

            T stepLength;

            public:
            explicit constexpr RangeIterator(T currentIndex_, T stepLength_ = 1) noexcept:
                currentIndex { currentIndex_ },
                stepLength   { stepLength_   }
            {
            }

            public:
            constexpr auto operator* () const noexcept -> T
            {
                return currentIndex;
            }

            constexpr auto operator++(   ) noexcept -> RangeIterator&
            {
                auto&& rhs = *this;

                rhs.currentIndex += rhs.stepLength;

                return rhs;
            }
            constexpr auto operator++(int) noexcept -> RangeIterator
            {
                auto&& lhs = *this;

                RangeIterator tmp(lhs);

                ++lhs;

                return tmp;
            }

            constexpr auto operator--(   ) noexcept -> RangeIterator&
            {
                auto&& rhs = *this;

                rhs.currentIndex -= rhs.stepLength;

                return rhs;
            }
            constexpr auto operator--(int) noexcept -> RangeIterator
            {
                auto&& lhs = *this;

                RangeIterator tmp(lhs);

                --lhs;

                return tmp;
            }

            friend constexpr auto operator!=(const RangeIterator& lhs, const RangeIterator& rhs) noexcept
            {
                if (lhs.stepLength >= 0)
                {
                    return lhs.currentIndex < rhs.currentIndex;
                }
                else
                {
                    return lhs.currentIndex > rhs.currentIndex;
                }
            }
        };

        private:
        RangeIterator rangeBegin;

        RangeIterator rangeEnd;

        public:
        explicit constexpr Range(T beginIndex_, T endIndex_, T stepLength_ = 1) noexcept:
            rangeBegin { beginIndex_, stepLength_ },
            rangeEnd   { endIndex_,   stepLength_ }
        {
        }

        public:
        constexpr auto begin ()       noexcept -> const RangeIterator&
        {
            return rangeBegin;
        }
        constexpr auto end   ()       noexcept -> const RangeIterator&
        {
            return rangeEnd;
        }

        constexpr auto begin () const noexcept -> const RangeIterator&
        {
            return rangeBegin;
        }
        constexpr auto end   () const noexcept -> const RangeIterator&
        {
            return rangeEnd;
        }
    };

    template<std::integral T>
    explicit Range(T beginIndex_, T endIndex_, T stepLength_ = 1) -> Range<T>;
}

#ifdef  D_AKR_TEST
#include <random>

namespace akr::test
{
    AKR_TEST(Range,
    {
        const auto test = [](auto beginIndex_, auto endIndex_, auto stepLength_)
        {
            auto count_ = std::size_t();

            for (auto i_ = beginIndex_; auto&& e_ : Range(beginIndex_, endIndex_, stepLength_))
            {
                assert(e_ == i_);

                i_ += stepLength_;

                count_++;
            }

            assert(count_ == static_cast<std::size_t>((endIndex_ - beginIndex_) / stepLength_)
                           + static_cast<std::size_t>((endIndex_ - beginIndex_) % stepLength_ != 0));
        };

        test(0, 10, +1);
        test(0, 10, +2);
        test(0, 10, +3);
        test(0, 10, +4);
        test(0, 10, +5);
        test(0, 10, +6);
        test(0, 10, +7);
        test(0, 10, +8);
        test(0, 10, +9);

        test(10, 0, -1);
        test(10, 0, -2);
        test(10, 0, -3);
        test(10, 0, -4);
        test(10, 0, -5);
        test(10, 0, -6);
        test(10, 0, -7);
        test(10, 0, -8);
        test(10, 0, -9);

        using T = std::int32_t;

        auto rd = std::random_device();
        auto re = std::mt19937_64(rd());

        const auto mm = static_cast<T>(std::sqrt(std::numeric_limits<T>::max()));

        auto id = std::uniform_int_distribution<T>(-mm, mm);

        for (auto i = 0; i < 100; i++)
        {
            const auto a = id(re);
            const auto b = id(re);

            auto c = id(re);

            if (a <= b)
            {
                for (; c < 0;)
                {
                    c = id(re);
                }
            }
            else
            {
                for (; c > 0;)
                {
                    c = id(re);
                }
            }

             //std::printf("[%07d] a: %6d, b: %6d, c: %6d\n", i, a, b, c);

            test(a, b, c);
        }
    });
}
#endif//D_AKR_TEST

#endif//Z_AKR_RANGE_HH
