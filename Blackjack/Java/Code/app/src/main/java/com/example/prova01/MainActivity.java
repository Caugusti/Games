package com.example.prova01;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.google.android.material.textfield.TextInputEditText;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private double banco, valorAposta;
    private TextInputEditText txtAposta;
    private TextView txtResultado, txtBanco, contViewUsuario, contViewApp;
    private ImageView carta1usuario, carta2usuario, carta3usuario, carta1app, carta2app, carta3app;
    private Integer usuarioCont, appCont;
    private String pUsuarioCarta, sUsuarioCarta, tUsuarioCarta, pAppCarta, sAppCarta, tAppCarta;
    private boolean jogando;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        txtAposta = findViewById(R.id.txtAposta);
        contViewUsuario = findViewById(R.id.usuarioCont);
        contViewApp = findViewById(R.id.appCont);
        txtResultado = findViewById(R.id.txtResultado);
        txtBanco = findViewById(R.id.txtBanco);
        banco = 1000.00;
        valorAposta = 0.00;
        txtBanco.setText("Banco: U$ " + banco);

        carta1usuario = (ImageView) findViewById(R.id.carta1usuario);
        carta2usuario = (ImageView) findViewById(R.id.carta2usuario);
        carta3usuario = (ImageView) findViewById(R.id.carta3usuario);
        carta1app = (ImageView) findViewById(R.id.carta1app);
        carta2app = (ImageView) findViewById(R.id.carta2app);
        carta3app = (ImageView) findViewById(R.id.carta3app);
        jogando = false;

    }

    public void apostar(View view){
        jogando = true;
        usuarioCont = 0;
        appCont = 0;
        contViewUsuario.setText(Integer.toString(usuarioCont));
        contViewApp.setText(Integer.toString(appCont));
        carta1usuario.setImageResource(R.drawable.padrao);
        carta2usuario.setImageResource(R.drawable.padrao);
        carta3usuario.setImageResource(R.drawable.padrao);
        carta1app.setImageResource(R.drawable.padrao);
        carta2app.setImageResource(R.drawable.padrao);
        carta3app.setImageResource(R.drawable.padrao);

        if (verifyBet()){
            pUsuarioCarta = getCard();
            sUsuarioCarta = getCard();
            pAppCarta = getCard();
            sAppCarta = getCard();

            setImage(carta1usuario, pUsuarioCarta);
            usuarioCont = setCont(usuarioCont, pUsuarioCarta);
            setImage(carta2usuario, sUsuarioCarta);
            usuarioCont = setCont(usuarioCont, sUsuarioCarta);
            contViewUsuario.setText(Integer.toString(usuarioCont));

            setImage(carta1app, pAppCarta);
            appCont = setCont(appCont, pAppCarta);
            contViewApp.setText(Integer.toString(appCont));
            appCont = setCont(appCont, sAppCarta);

            if (usuarioCont == 21){
                banco += valorAposta;
                txtResultado.setText("Blackjack! Você venceu! \n Clique em Apostar para jogar novamente.");
                jogando = false;
            }

            else if (appCont == 21){
                banco -= valorAposta;
                setImage(carta2app, sAppCarta);
                contViewApp.setText(Integer.toString(appCont));
                txtResultado.setText("Você perdeu! Blackjack para o Oponente. \n Clique em Apostar para jogar novamente.");
                jogando = false;
            }

            else {
                txtResultado.setText("Escolha se deseja pegar mais uma carta.");
            }

        }
    }

    public void outraCarta(View view){
        if (jogando == true) {
            tUsuarioCarta = getCard();
            setImage(carta3usuario, tUsuarioCarta);
            usuarioCont = setCont(usuarioCont, tUsuarioCarta);
            contViewUsuario.setText(Integer.toString(usuarioCont));

            setImage(carta2app, sAppCarta);

            if (appCont < 15) {
                tAppCarta = getCard();
                setImage(carta3app, tAppCarta);
                appCont = setCont(appCont, tAppCarta);
            }

            contViewApp.setText(Integer.toString(appCont));
            verifyResults();
        }
    }

    public void continuarJogo(View view){
        if (jogando == true) {
            setImage(carta2app, sAppCarta);

            if (appCont < 15) {
                tAppCarta = getCard();
                setImage(carta3app, tAppCarta);
                appCont = setCont(appCont, tAppCarta);
            }

            contViewApp.setText(Integer.toString(appCont));
            verifyResults();
        }
    }

    public void verifyResults(){
        if (usuarioCont > 21) {
            banco -= valorAposta;
            txtResultado.setText("Você perdeu, pois ultrapassou os 21. \n Clique em Apostar para jogar novamente.");
        }

        else if (appCont > 21) {
            banco += valorAposta;
            txtResultado.setText("Seu oponente ultrapassou os 21. Você venceu! \n Clique em Apostar para jogar novamente.");
        }
        else if (usuarioCont == 21) {
            banco += valorAposta;
            txtResultado.setText("Blackjack! Você venceu! \n Clique em Apostar para jogar novamente.");
        }

        else if (appCont == 21){
            banco -= valorAposta;
            txtResultado.setText("Você perdeu! Blackjack para o Oponente. \n Clique em Apostar para jogar novamente.");
        }

        else if (usuarioCont == appCont) {
            txtResultado.setText("Empatou! \n Clique em Apostar para jogar novamente.");
        }

        else if (usuarioCont > appCont) {
            banco += valorAposta;
            txtResultado.setText("Você venceu! Chegou mais perto. \n Clique em Apostar para jogar novamente.");
        }

        else {
            banco -= valorAposta;
            txtResultado.setText("Você perdeu! \n Clique em Apostar para jogar novamente.");
        }

        jogando = false;
        txtBanco.setText("Banco: U$ " + banco);
    }

    public void novoJogo(View view){
        banco = 1000.00;
        txtBanco.setText("Banco: U$ " + banco);
        carta1usuario.setImageResource(R.drawable.padrao);
        carta2usuario.setImageResource(R.drawable.padrao);
        carta3usuario.setImageResource(R.drawable.padrao);
        carta1app.setImageResource(R.drawable.padrao);
        carta2app.setImageResource(R.drawable.padrao);
        carta3app.setImageResource(R.drawable.padrao);
        txtResultado.setText("Faça sua aposta!");
        usuarioCont = 0;
        appCont = 0;
        contViewUsuario.setText(Integer.toString(usuarioCont));
        contViewApp.setText(Integer.toString(appCont));
    }

    public boolean verifyBet() {
        String aposta = txtAposta.getText().toString();

        if (aposta == null || aposta.equals("")) {
            txtResultado.setText("Aposta inválida. Por favor, tente novamente.");
            return false;
        }
        else {
            valorAposta = Double.parseDouble(aposta);

            if (valorAposta > banco || valorAposta == 0.00) {
                txtResultado.setText("Aposta inválida. Por favor, insira novo valor, ou inicie um novo jogo.");
                return false;
            }
            else {
                return true;
            }
        }
    }

    public String getCard(){
        String [] cartas = {"as", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove", "dez", "valete", "dama", "rei"};
        int num = new Random().nextInt(13);

        return cartas[num];
    }

    public void setImage(ImageView imagemCarta, String carta){
        switch (carta){
            case "as":
                imagemCarta.setImageResource(R.drawable.as);
                break;

            case "dois":
                imagemCarta.setImageResource(R.drawable.dois);
                break;

            case "tres":
                imagemCarta.setImageResource(R.drawable.tres);
                break;

            case "quatro":
                imagemCarta.setImageResource(R.drawable.quatro);
                break;

            case "cinco":
                imagemCarta.setImageResource(R.drawable.cinco);
                break;

            case "seis":
                imagemCarta.setImageResource(R.drawable.seis);
                break;

            case "sete":
                imagemCarta.setImageResource(R.drawable.sete);
                break;

            case "oito":
                imagemCarta.setImageResource(R.drawable.oito);
                break;

            case "nove":
                imagemCarta.setImageResource(R.drawable.nove);
                break;

            case "dez":
                imagemCarta.setImageResource(R.drawable.dez);
                break;

            case "valete":
                imagemCarta.setImageResource(R.drawable.valete);
                break;

            case "dama":
                imagemCarta.setImageResource(R.drawable.dama);
                break;

            case "rei":
                imagemCarta.setImageResource(R.drawable.rei);
                break;
        }
    }

    public Integer setCont (Integer cont, String carta){
        switch (carta) {
            case "as":
                cont += 11;
                break;

            case "dois":
                cont += 2;
                break;

            case "tres":
                cont += 3;
                break;

            case "quatro":
                cont += 4;
                break;

            case "cinco":
                cont += 5;
                break;

            case "seis":
                cont += 6;
                break;

            case "sete":
                cont += 7;
                break;

            case "oito":
                cont += 8;
                break;

            case "nove":
                cont += 9;
                break;

            case "dez":
            case "valete":
            case "dama":
            case "rei":
                cont += 10;
                break;
        }

        return cont;
    }
}