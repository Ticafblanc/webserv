import React from 'react'
import ReactDOM from 'react-dom/client'
import Home from "./Home.tsx";
import '../../sass/custom.sass'
import '../css/App.css'
import {BrowserRouter, Routes, Route} from "react-router-dom";
import FormPage from "./FormPage.tsx";

ReactDOM.createRoot(document.getElementById('root') as HTMLElement).render(
  <React.StrictMode>
      <>
          <BrowserRouter>
              <Routes>
                  <Route index element={<Home/>} />
                  <Route path={"/home"} element={<Home/>} />
                  <Route path={"/form"} element={<FormPage/>} />
              </Routes>
          </BrowserRouter>
      </>
  </React.StrictMode>,
)
