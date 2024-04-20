#include <vector>
#include <iostream>

#define max_val 1
#define min_val -1

// siirtogeneraattori
std::vector<int> get_legal_moves(int n)
{
    std::vector<int> retval;
    for (int i = 1; (i <= n) && (i <= 3); ++i)
      retval.push_back(i);
    
    return retval;
}

// pelipuuhaku
int minimax(int const n, bool const max)
{
    if (n == 0)
        return max ? max_val : min_val;
    if (n == 1)
        return max ? min_val : max_val;

    std::vector<int> mv = get_legal_moves(n); /* get legal moves palauttaa vektorin laillisista siirroista, esim. 1,2,3 */
    int best_val;
    if (max) {
        best_val = min_val;
        for (int const lm : mv) {
            int const val = minimax(n - lm, false);
            if (val > best_val)
                best_val = val;
        }
    } else { // min
        best_val = max_val;
        for (int const lm : mv) {
            int const val = minimax(n - lm, true);
            if (val < best_val)
                best_val = val;
        }
    }
    return best_val;
}


int main(void) {
    int n = minimax(30, true);
    std::cout << n << std::endl;
    return 0;
}
