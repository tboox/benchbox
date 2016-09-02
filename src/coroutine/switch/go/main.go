/* //////////////////////////////////////////////////////////////////////////////////////
 * imports
 */
package main
import (
    "fmt"
    "runtime"
    "time"
    )

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
const COUNT = 10000000

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
func switchtask(count int){

    var i = 0
    for {

       i++
       if i > count {
           break
       }

       runtime.Gosched()
   }
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
func main(){

    // single cpu
    runtime.GOMAXPROCS(1)

    // init duration
    var duration = time.Now().UnixNano()

    // create coroutine task
    go switchtask(COUNT >> 1)

    // in main goroutine
    switchtask(COUNT >> 1)

    // computing time
    duration = (time.Now().UnixNano() - duration) / 1000000

    // trace
    fmt.Printf("switch: go: %d switches in %d ms, %d switches per second\n", COUNT, duration, (1000 * COUNT) / duration)
}
