## Threads Task Notes

#### `std::string_view`

It's is a **lightweight, non-owning view** of a string.

That means:

- It **does NOT own memory**
- It just points to existing characters
- No copying, no allocation
- Super fast
- Read-only

#### `std::condition_variable`

`std::condition_variable` lets a thread:

- Sleep until a condition becomes true
- Be woken up by another thread
- Automatically release & re-lock a mutex

You use it together with:

- `std::mutex`
- `std::unique_lock<std::mutex>` (not `lock_guard`!)

`notify_one()` for single consumer

`notify_all()` for multiple consumers

`cv.wait(lock, []{ return condition; })` Waits until condition becomes true, `std::unique_lock<std::mutex> lock(mtx)`, `std::mutex mtx`