import React from 'react'
import Footer from './Footer';
const Contact = () => {
    return (
        <>
            <div className="contact">
                <div className="contact__header">
                    <h1>Contact Us</h1>
                </div>
                <div className="contact__content">
                    <p>
                        If you have any questions or suggestions please feel free to contact me with the information below. 
                        <br></br>
                        I would be very happy to receive your feedback and to answer all of your questions.
                        
                    </p>
                   
                    <div className="contact__social">
                        <div className="contact__social__item">
                            <i className="fab fa-facebook-square icon fb"></i>
                            <a href="https://www.facebook.com/DangKhoaPika/">Đăng Khoa Pika</a>
                        </div>
                        <div className="contact__social__item">
                            <i className="fab fa-github-square icon gh"></i>
                            <a href="https://github.com/Pika0546">Pika0546</a>
                        </div>
                        <div className="contact__social__item">
                            <i className="far fa-envelope icon gm"></i>
                            <span>dangkhoa.it.23@gmail.com</span>
                        </div>
                    </div>
                </div>
            </div>
            <Footer></Footer>
        </>
    )
}

export default Contact
