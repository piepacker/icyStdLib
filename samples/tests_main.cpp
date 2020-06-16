
#include "StringUtil.h"
#include "StringTokenizer.h"

static const char* parse_inputs[] = {
    "",
    "--lvalue=rvalue1",
    "--lvalue=rvalue1,revalue2",
    "--lvalue=rvalue1,revalue2,three",
    "--lvalue = rvalue1, rvalue2",
    "--lvalue\t=\trvalue1,\trevalue2",
    "--lvalue=",
    "--lvalue",
    " --lvalue = はい。 , はい。, おはようございます",
    " --値 = はい。 , はい。, おはようございます",
    nullptr,
};

// note: verification is done by bash script externally.
/* Expected output, use diff CLI too to verify:
--lvalue
--lvalue = rvalue1
--lvalue = rvalue1,revalue2
--lvalue = rvalue1,revalue2,three
--lvalue = rvalue1,rvalue2
--lvalue = rvalue1,revalue2
--lvalue

--lvalue = はい。,はい。,おはようございます
--値 = はい。,はい。,おはようございます

*/

int main(int argc, char** argv) {

    for(const auto* item : parse_inputs) {
        auto tok = Tokenizer(item);
        if (auto* lvalue = tok.GetNextTokenTrim('=')) {
            printf("%s", lvalue);
            bool need_comma = 0;
            while(auto* rparam = tok.GetNextTokenTrim(',')) {
                printf("%s%s", need_comma ? "," : "=", rparam);
                need_comma = 1;
            }
        }
        printf("\n");

    }
    printf("\n");
    return 0;
}
