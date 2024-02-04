import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse

def get_internal_links_recursive(url, visited_pages, internal_links, visited_links):
    # Add the URL to the set of visited pages
    visited_pages.add(url)

    # Fetch the page content
    response = requests.get(url)
    if response.status_code == 200:
        page_html = response.text

        # Parse the HTML content of the page
        soup = BeautifulSoup(page_html, 'html.parser')

        # Extract all anchor tags (links)
        for link in soup.find_all('a', href=True):
            href = link['href']

            # Check if the link is a page anchor (starts with '#') or leads to a page already visited
            if href.startswith('#') or urljoin(url, href) in visited_links:
                continue

            # Join the URL to handle relative paths
            full_url = urljoin(url, href)

            # Parse the full URL
            parsed_url = urlparse(full_url)

            # Check if the URL belongs to the same domain and has not been visited yet
            if parsed_url.netloc == urlparse(url).netloc and full_url not in visited_pages:
                # Check if the link starts with the desired prefix
                if full_url.startswith("https://en.cppreference.com/w/cpp"):
                    internal_links.add(full_url)

                    # Print the link as it is discovered
                    print(full_url)

                    # Write the link to the file
                    with open("links.txt", "a") as f:
                        f.write(full_url + "\n")

                    # Recursively crawl the internal link
                    get_internal_links_recursive(full_url, visited_pages, internal_links, visited_links)

            # Add the link to the set of visited links
            visited_links.add(full_url)

if __name__ == "__main__":
    # Get the homepage URL from the user
    homepage_url = input("Enter the homepage URL: ")

    # Set to keep track of visited pages to avoid crawling the same page multiple times
    visited_pages = set()

    # Set to store internal links
    internal_links = set()

    # Set to store visited links
    visited_links = set()

    # Start recursive crawling from the homepage
    get_internal_links_recursive(homepage_url, visited_pages, internal_links, visited_links)

    print("Links saved to 'links.txt'")

