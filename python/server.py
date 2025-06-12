import asyncio

async def handle_client(reader, writer):
    while True:
        data = await reader.read(1024)
        if not data:
            break
        writer.write(data)
        await writer.drain()
    writer.close()

async def main():
    server = await asyncio.start_server(handle_client, '127.0.0.1', 6999)
    print("Python server listening on port 6999")
    async with server:
        await server.serve_forever()

asyncio.run(main())

