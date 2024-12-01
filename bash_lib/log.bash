c_rst="\e[0m"
c_red="\e[31m"
c_green="\e[32m"
c_yellow="\e[33m"
c_grey="\e[90m"

function preamble() { echo -n "$(date "+%T") [aoc]"; }
function log::debug() {
  [ -z "${DEBUG}" ] && return
  echo -e "${c_grey}$(preamble) DEBUG::${c_rst} $*" >&2
}
function log::info()  { echo -e "${c_green}$(preamble) INFO::${c_rst} $*" >&2; }
function log::warn() { echo -e "${c_yellow}$(preamble) WARN::${c_rst} $*" >&2; }
function log::err()      { echo -e "${c_red}$(preamble) ERR::${c_rst} $*" >&2; }
