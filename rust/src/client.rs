use std::time::Instant;
use tokio::net::TcpStream;
use tokio::io::{AsyncReadExt, AsyncWriteExt};

const MSG: &[u8] = &[1u8; 100];
const CLIENTS: usize = 10000;

#[tokio::main]
async fn main() {
    let mut handles = vec![];
    let start = Instant::now();

    for _ in 0..CLIENTS {
        handles.push(tokio::spawn(async {
            let mut stream = TcpStream::connect("127.0.0.1:8080").await.unwrap();
            stream.write_all(MSG).await.unwrap();
            let mut buf = [0u8; 100];
            stream.read_exact(&mut buf).await.unwrap();
        }));
    }

    for h in handles {
        h.await.unwrap();
    }

    println!(
        "Rust: {} clients, total time = {:?}, avg = {:?}",
        CLIENTS,
        start.elapsed(),
        start.elapsed() / CLIENTS as u32
    );
}

