import Form from 'react-bootstrap/Form'

interface Props {
    label: string,
    formControlType: string,
    placeHolder: string,
    formName: string;
}
function MyFormGroup(props: Props) {
    return (
        <>
            <Form.Label>{props.label}</Form.Label>
            <Form.Control name={props.formName} type={props.formControlType} placeholder={props.placeHolder} />
        </>
    );
}

export default MyFormGroup;