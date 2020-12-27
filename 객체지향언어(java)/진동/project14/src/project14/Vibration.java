package project14;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Vibration {
	
	JFrame frame;
	JButton btn;
	
	Thread thread;
	
	private Vibration() {
		frame = new JFrame("Vibration");
		
		buildGUI();
		
		frame.setSize(200,200);
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
	
	private void buildGUI() {
		btn = new JButton("진동시작");
		frame.add(btn);
		
		btn.addActionListener(handler);
	}

	
	private ActionListener handler = new ActionListener() {
		private boolean cont = true;
		
		
		@Override
		public void actionPerformed(ActionEvent e) {
			
			String s = e.getActionCommand();
			
			if(s.equals("진동시작")) {
				btn.setText("진동끝");
				
				// 진동처리
				thread = new Thread(new VibrationThread());
				thread.start();
			}
			else {
				//진동 멈춤 처리
				btn.setText("진동시작");
				//cont = false;
				thread = null;
			}
			
			
		}
		
	};
	/*
	class VibrationRunnable implements Runnable {
		
		private int offset = 10;

		@Override
		public void run() {
			while(thread == Thread.currentThread()) {
				frame.setLocation(frame.getLocation().x + offset, frame.getLocation().y);
			
				offset = -offset;
				
				try {
					Thread.sleep(100);
				} catch(InterruptedException e1 ) {		}
			}
		}
		
	}*/
	
	class VibrationThread extends Thread {
		
		private int offset = 10;

		@Override
		public void run() {
			while(thread == Thread.currentThread()) {
				frame.setLocation(frame.getLocation().x + offset, frame.getLocation().y);
			
				offset = -offset;
				
				try { //지연취소
					Thread.sleep(100);
				} catch(InterruptedException e1 ) {		}
			}
		}
		
	}
	
	public static void main(String[] args) {
		new Vibration();
	}
}

