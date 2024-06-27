import requests


with open('url.txt','r') as f:
    url=f.read()

print("RUN")
print(url)

# Example headers (modify as needed)
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
}

# Cloudflare often requires a valid User-Agent header
response = requests.get(url, headers=headers)

# Check if the request was successful (status code 200)
if response.status_code == 200:
    print(response.text)
else:
    print(f"Failed to retrieve data: {response.status_code}")

    
