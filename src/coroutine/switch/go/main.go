/* //////////////////////////////////////////////////////////////////////////////////////
 * imports
 */
package main
import (
    "os"
    "fmt"
    "strconv"
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

    // get coroutine count
    cocount := 2
    if len(os.Args) > 1 {
        cocount, _ = strconv.Atoi(os.Args[1])
    }

    // init duration
    var duration = time.Now().UnixNano()

    // create coroutine task
    var i = 0
    for {

        i++
        if i > cocount - 1 {
           break
        }

        go switchtask(COUNT / cocount)
    }

    // in main goroutine
    switchtask(COUNT / cocount)

    // computing time
    duration = (time.Now().UnixNano() - duration) / 1000000

    // trace
    fmt.Printf("switch[%d]: go: %d switches in %d ms, %d switches per second\n", cocount, COUNT, duration, (1000 * COUNT) / duration)
}
