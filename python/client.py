import asyncio
import time

CLIENTS = 10000

async def run_client():
    reader, writer = await asyncio.open_connection('127.0.0.1', 6999)
    msg = b'\x01' * 100
    writer.write(msg)
    await writer.drain()
    await reader.readexactly(100)
    writer.close()
    await writer.wait_closed()

async def main():
    start = time.time()
    await asyncio.gather(*[run_client() for _ in range(CLIENTS)])
    elapsed = (time.time() - start) * 1000  # in ms
    avg = elapsed / CLIENTS
    print(f"Python: {CLIENTS} clients, total time = {elapsed:.2f} ms, avg latency = {avg:.4f} ms/client")

asyncio.run(main())

