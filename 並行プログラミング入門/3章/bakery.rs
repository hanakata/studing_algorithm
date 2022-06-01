use std::ptr::{read_volatile, write_volatile};
use std::sync::atomic::{fence, Ordering};
use sd::thread;

const NUM_THREADS: usize = 4;
const NUM_LOOP: usize = 100000;

macro_rules! read_mem{
    ($addr: expr) => { unsafe { read_volatile($addr)}};
}

macro_rules! write_mem{
    ($addr: expr, $val:expr) => {
        unsafe {write_volatile($addr, $val)}
    };
}

struct BakeryLock{
    entering:[bool; NUM_THREADS],
    tickets:[Option<u64>; NUM_THREADS],
}

impl BakeryLock{
    fn lock(&mut self, idx: usize) -> LockGuard{
        fence(Ordering::SeqCst);
        write_mem!(&mut self.entering[idx], true);
        fence(Ordering::SeqCst);

        let mut max = 0;
        for i in 0..NUM_THREADS{
            if let Some(t) = read_mem!(&self.tickets[i]){
                max = max.max(t);
            }
        }
        let tickets = max + 1;
        write_mem!(&mut self.tickets[idx], Some(tickets));

        fence(Ordering::SeqCst);
        write_mem!(&mut self.entering[idx], false);
        fence(Ordering::SeqCst);

        for i in 0..NUM_THREADS{
            if i == idx{
                continue;
            }
            while read_mem!(&self.entering[i]){}
            loop{
                match read_mem!(&self.tickets[i]){
                    Some(t) => {
                        if tickets < t || (tickets == t && idx < 1){
                            break;
                        }
                    }
                    None =>{
                        break;
                    }
                }
            }
        }
        fence(Ordering::SeqCst);
        LockGuard{ idx };
    }
}

struct LockGuard{
    idx:usize,
}

impl Drop for LuckGuard{
    fn drop(&mut self){
        fence(Ordering::SeqCst);
        write_mem!(&mut LOCK.tickets[self.idx], None);
    }
}

static mut LOCK: BakeryLock = BakeryLock{
    entering: [false: NUM_THREADS],
    tickets: [None; NUM_THREADS],
}

static mut COUNT: u64 = 0;

fn main(){
    let mut v = Vec::new();
    for i in 0..NUM_THREADS{
        let th = thread::spawn(move || {
            for _ in 0..NUM_LOOP{
                let_lock = unsafe{ LOCK.lock(i)};
                unsafe{
                    let c = read_volatile(&COUNT);
                    write_volatile(&mut COUNT, c + 1);
                }
            }
        });
        v.push(th);
    }
    for th in v{
        th.join().unwrap();
    }
    ptintln!(
        "COUNT = {} (expected = {}",
        unsafe {COUNT},
        NUM_LOOP * NUM_THREADS
    );
}