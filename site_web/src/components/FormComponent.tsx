import MyFormGroup from './MyFormGroup.tsx';
// import {ChangeEvent, FormEvent, useState} from "react";
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';

import '../css/App.css'

function FormComponent() {
    // const [name, setName] = useState('');
    // const [lastName, setLastName] = useState('');
    // const [email, setEmail] = useState('');
    // const [date, setDate] = useState('');
    //
    //
    // const nameChanger = (event: ChangeEvent<HTMLInputElement>) => {
    //     setName(event.target.value);
    // }
    // const lastNameChanger = (event: ChangeEvent<HTMLInputElement>) => {
    //     setLastName(event.target.value);
    // }
    // const emailChanger = (event: ChangeEvent<HTMLInputElement>) => {
    //     setEmail(event.target.value);
    // }
    // const dateChanger = (event: ChangeEvent<HTMLInputElement>) => {
    //     setDate(event.target.value);
    // }
    //
    // const handleSubmit = (event: FormEvent<HTMLFormElement>) => {
    //     event.preventDefault();
    //     console.log(name, lastName, email, date);
    // }

    return (
        <div className="divFormInner bg-primary">
            <Form action="http://localhost:8000/cgi.php" method="post" encType="multipart/form-data">
                <Form.Group className="mb-3" controlId="floatingName">
                    <MyFormGroup label={"Name"} formControlType={"string"} placeHolder={"Name"} formName={"name"}/>
                </Form.Group>
                <Form.Group className="mb-3" controlId="floatingLastName">
                    <MyFormGroup label={"Last name"} formControlType={"string"} placeHolder={"Last name"} formName={"lastName"}/>
                </Form.Group>
                <Form.Group className="mb-3" controlId="floatingEmail">
                    <MyFormGroup label={"Email"} formControlType={"email"} placeHolder={"Email"} formName={"email"}/>
                </Form.Group>
                <Form.Group className="mb-3" controlId="floatingBirthdate">
                    <MyFormGroup label={"Birthdate"} formControlType={"date"} placeHolder={"Birthday"} formName={"birthDay"}/>
                </Form.Group>
                <Form.Group className="mb-3">
                    <MyFormGroup label={"File"} formControlType={"file"} placeHolder={"file"} formName={"file"}/>
                </Form.Group>
                <div className="d-grid gap-2 mb-3">
                    <Button className="centerButton" variant="secondary" type="submit">Envoyer</Button>
                </div>
            </Form>
        </div>
    );
}

export default FormComponent;