import requests

# Fonction pour tester une requête GET simple
def test_get(url):
    response = requests.get(url)
    print(f"GET {url}: {response.status_code}")
    return response

# Fonction pour tester une requête POST
def test_post(url, data):
    response = requests.post(url, data=data)
    print(f"POST {url}: {response.status_code}")
    return response

# Fonction pour tester une requête DELETE
def test_delete(url):
    response = requests.delete(url)
    print(f"DELETE {url}: {response.status_code}")
    return response

# Test de la redirection et des pages d'erreur par défaut
def test_redirection_and_errors(url):
    response = requests.get(url, allow_redirects=False)
    print(f"Redirection {url}: {response.status_code}")
    if response.status_code in [301, 302, 303, 307]:
        print(f"Location: {response.headers['Location']}")
    return response

# Exemple d'utilisation
if __name__ == "__main__":
    # Remplacez 'http://localhost:8080' par l'URL de votre serveur
    base_url = 'http://localhost:8080'
    test_get(base_url)
    test_post(f"{base_url}/post_endpoint", {"key": "value"})
    test_delete(f"{base_url}/resource_to_delete")
    test_redirection_and_errors(f"{base_url}/redirect_me")