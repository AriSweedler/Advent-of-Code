command! Stroids :source /Users/ari/dev/AoC/challenge10/stroids.vim | call Stroids()

function! Stroids()
  " Arguments to "setpos" = [bufnum, lnum, col, off]
  let upperLeft = [0, 1, 1, 0]
  call setpos(".", upperLeft)

  " Loop through each line, reading into a 2D array
  let stroids = []
  let lnum = 1
  while lnum <= line("$")
    let stroidline = []
    let cnum = 1
    while cnum <= col("$")
      "echom "Row: " . l:lnum . ", Col: " . l:cnum . "!"
      let cnum = cnum + 1
      call add(stroidline, '!')
    endwhile
    let lnum = lnum + 1
    call add(stroids, stroidline)
  endwhile
endfunction
