import Button from "react-bootstrap/Button";

function Home() {
    return (
        <>
            <div className="text-center">
                <h1>Welcome to Webserv</h1>
                <Button href="/form" className="text-center" variant="primary">Form</Button>
            </div>
        </>
    )
}

export default Home;