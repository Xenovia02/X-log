#include "record.hpp"

namespace xlog
{
    
    Recod::Record(const std::string& fl, const uchar& ln, const std::string fn, str_pair_t arg_pairs)
        : file(fl), line(ln), func(fn), args(arg_pairs.begin(), arg_pairs.end()) { }

    Record::Record(const std::string& fl, const uchar& ln, str_pair_t arg_pairs)
        : file(fl), line(ln), func("unavailable"), args(arg_pairs.begin(), arg_pairs.end()) { }

    Record::Record(Record&& old)
    {
        args = std::move(old.args);
        msg = std::move(old.msg);
        lgr = std::move(old.lgr);
        lvl = old.lvl;
        file = std::move(old.file);
        line = old.line;
    }

    void Record::init_rest(const std::string& message, const std::string& lname, const uchar& level)
    {
        msg = message;
        lgr = lname;
        lvl = level;
    }

    arg_map_t Record::get_dict() const
    {
        arg_map_t dict
        {
            { "msg" , msg                  },
            { "lgr" , lgr                  },
            { "file", file                 },
            { "lvl" , std::to_string(lvl)  },
            { "line", std::to_string(line) },
        };
        dict.insert(args.begin(), args.end());
        return dict;
    }

#ifdef CPP20
    Record::Record(const std::source_location& info, const arg_map_t& arg_pairs)
        : file(info.file_name()),
          line(info.line()),
          func(info.function_name()),
          args(arg_pairs.begin(), arg_pairs.end()) { }
#endif

}
