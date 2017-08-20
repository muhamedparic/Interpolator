#ifndef TEST_DIAMOND_SEARCH_H
#define TEST_DIAMOND_SEARCH_H

class Test_diamond_search
{
public:
    Test_diamond_search();
    template <typename T1, typename T2>
    bool compare(const T1& val1, const T2& val2);

private:
    void identical_frames();
    void random_frames();
    void shift();

};

#endif // TEST_DIAMOND_SEARCH_H
