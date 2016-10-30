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
func channeltask(channel <-chan int){

    for {

        <- channel
    }
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
func main(){

    // single cpu
    runtime.GOMAXPROCS(1)

    // get channel size
    size := 0
    if len(os.Args) > 1 {
        size, _ = strconv.Atoi(os.Args[1])
    }

    // make channel
    channel := make(chan int, size)

    // init duration
    duration := time.Now().UnixNano()

    // create coroutine task
    go channeltask(channel)

    // in main goroutine
    count := COUNT
    for {

        count--
        channel <- count
        if count == 0 {
            break
        }
    }

    // computing time
    duration = (time.Now().UnixNano() - duration) / 1000000

    // trace
    fmt.Printf("channel[%d]: go: %d passes in %d ms, %d passes per second\n", size, COUNT, duration, (1000 * COUNT) / duration)
}
