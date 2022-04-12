## [TinyBuffer](src/TinyBuffer.h)

The 16-byte ring buffer implementation. This implementation does not perform any validation (i.e. it is possible to "get" when "empty" and "put" when "full"), the caller is expected to maintain the buffer consistency.
<pre>
Head and tail indices are incremented "from left to right".
Start over from the left-hand side on overflow.
"X" - some value, " " - some garbage.
ex.1.
     [ XXXXXXXXX      ] 9/16
      ↑        ↑       
   tail     head       
ex.2.
     [XXXXX          X] 6/16
          ↑         ↑  
       head      tail  
</pre>

### Class TinyBuffer

|Method|Parameters|Return|Description|
|-|-|-|-|
|countBusy||count|Get the size of data.|
|countFree||count|Get the size of free space.|
|clear|||Mark the buffer as empty.|
|put|value||Advance the buffer head and put one byte into head.|
|get||value|Advance the buffer tail and get one byte.|
|peek||value|Peek the value at the next buffer index.|
|skip|||Advance the buffer tail.|
